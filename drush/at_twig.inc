<?php
/**
 * @file drush/at_twig.inc
 */

/**
 * Callback for twig:doc drush command.
 */
function drush_at_twig_doc($name = 'all') {
  switch ($name) {
    case 'function':
    case 'functions':
      drush_at_twig_doc__list__function();
      break;

    case 'filter':
    case 'filters':
      drush_at_twig_doc__list__filter();
      break;

    case '':
    case 'all':
      drush_print('Functions', 2);
      drush_at_twig_doc__list__function();
      drush_print('Filters', 2);
      drush_at_twig_doc__list__filter();
      break;

    default:
      drush_at_twig_doc__item($name);
      break;
  }
}

function drush_at_twig_doc__list__function() {
  foreach (array_keys(at_container('twig_string')->getFunctions()) as $name) {
    drush_print(" - $name", 4);
  }
  drush_print("", 4);
}

function drush_at_twig_doc__list__filter() {
  foreach (array_keys(at_container('twig_string')->getFilters()) as $name) {
    drush_print(" - $name", 4);
  }
  drush_print("", 4);
}

function drush_at_twig_doc__item($name) {
  foreach (at_container('twig_string')->getFilters() as $filter_name => $filter) {
    if ($name === $filter_name) {
      drush_at_twig_doc__item__table($filter);
    }
  }

  foreach (at_container('twig_string')->getFunctions() as $fn_name => $fn) {
    if ($name === $fn_name) {
      drush_at_twig_doc__item__table($fn);
    }
  }
}

function drush_at_twig_doc__item__table($obj) {
  drush_print_table(array(
    array('Property',   'Value'),
    array('----------', '---------------------'),
    array('Name',       $obj->getName()),
    array('Callable',   $obj->getCallable()),
    array('Node Class', $obj->getNodeClass()),
    array('Arguments',  '[' . implode(', ', $obj->getArguments()) . ']'),
    array('Safe',       (int) $obj->getSafe()),
  ), TRUE);
}
